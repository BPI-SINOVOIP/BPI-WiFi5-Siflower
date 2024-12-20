
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <pthread.h>


#include <netlink-local.h>
#include <netlink/netlink.h>
#include <netlink/utils.h>
#include <netlink/cache.h>
#include <netlink/attr.h>
#include <netlink/msg.h>
#include <linux/socket.h>


#include <arpa/inet.h>
#include <netinet/in.h>

#include <linux/rtnetlink.h>
#include <linux/sockios.h>
#include <linux/ip.h>
#include <linux/if_addr.h>
#include <linux/if_link.h>

#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <glob.h>
#include <time.h>
#include <unistd.h>

#include <unl.h>
#include <libubox/uloop.h>

#include <syslog.h>
#include <errno.h>
#define LOG(X,...) syslog(LOG_CRIT,X,##__VA_ARGS__)

#define t_assert(x) { \
					 if(!(x))  {err = -__LINE__;goto error;} \
}

#define BUFLEN 1024
static char dev_buf[256];

static int system_get_sysctl(const char *path, char *buf, const size_t buf_sz)
{
	int fd = -1, ret = -1;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		goto out;

	ssize_t len = read(fd, buf, buf_sz - 1);
	if (len < 0)
		goto out;

	ret = buf[len] = 0;

out:
	if (fd >= 0)
		close(fd);

	return ret;
}

static int
system_get_dev_sysctl(const char *path, const char *device, char *buf, const size_t buf_sz)
{
    snprintf(dev_buf, sizeof(dev_buf), path, device);
    return system_get_sysctl(dev_buf, buf, buf_sz);
}

void parse_rtattr(struct rtattr **tb, int max, struct rtattr *attr, int len)
{
	for (; RTA_OK(attr, len); attr = RTA_NEXT(attr, len)) {
		if (attr->rta_type <= max) {
			tb[attr->rta_type] = attr;
		}
	}
}

void print_ifinfomsg(struct nlmsghdr *nh)
{
	int len;
	int link_state = 0;
	char buf[10], buffer[20];
	struct rtattr *tb[IFLA_MAX + 1];
	struct ifinfomsg *ifinfo;
	bzero(tb, sizeof(tb));
	ifinfo = NLMSG_DATA(nh);
	len = nh->nlmsg_len - NLMSG_SPACE(sizeof(*ifinfo));
	parse_rtattr(tb, IFLA_MAX, IFLA_RTA (ifinfo), len);
	if(tb[IFLA_IFNAME]) {
		LOG("%s\n", RTA_DATA(tb[IFLA_IFNAME]));
		if (!system_get_dev_sysctl("/sys/class/net/%s/carrier", "eth0", buf, sizeof(buf)))
		{
			link_state = strtoul(buf, NULL, 0);
			//LOG("link_state is %d\n",link_state);
			sprintf(buffer,"ap_mode_led %d",link_state);
			system(buffer);
		}
	}
}

int main(int argc, char *argv[])
{
	int socket_fd;
	int err = 0;
	fd_set rd_set;
	struct timeval timeout;
	int select_r;
	int read_r;
	struct sockaddr_nl sa;
	struct nlmsghdr *nh;


	int len = BUFLEN;
	char buff[1024];

	/*打开NetLink Socket*/
	socket_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	t_assert(socket_fd > 0);
	t_assert(!setsockopt(socket_fd, SOL_SOCKET, SO_RCVBUF, &len, sizeof(len)));

	/*设定接收类型并绑定Socket*/
	bzero(&sa, sizeof(sa));
	sa.nl_family = AF_NETLINK;
	sa.nl_groups = RTMGRP_LINK;
	t_assert(!bind(socket_fd, (struct sockaddr *) &sa, sizeof(sa)));
	while (1) {
		FD_ZERO(&rd_set);
		FD_SET(socket_fd, &rd_set);
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		select_r = select(socket_fd + 1, &rd_set, NULL, NULL, &timeout);
		if (select_r < 0) {
			LOG("select error\n");

		} else if (select_r > 0) {
			if (FD_ISSET(socket_fd, &rd_set)) {
				read_r = read(socket_fd, buff, sizeof(buff));
				for (nh = (struct nlmsghdr *) buff; NLMSG_OK(nh, read_r); nh = NLMSG_NEXT(nh, read_r)) {
					switch (nh->nlmsg_type) {
						default:
						LOG("nh->nlmsg_type = %d\n", nh->nlmsg_type);
						break;
						case NLMSG_DONE:
						case NLMSG_ERROR:
						break;
						case RTM_NEWLINK:
						case RTM_DELLINK:
						case RTM_GETLINK:
						print_ifinfomsg(nh);
						break;
					}


				}

			}

		}

	}

	close(socket_fd);

error:
	if (err < 0) {
		LOG("Error at line %d\nErrno=%d\n", -err, errno);
	}
	return err;

}

