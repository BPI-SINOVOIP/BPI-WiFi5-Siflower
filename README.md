# BPI-WiFi5-Siflower

----------

### **Prepare**

To compile the BPI-WiFi5-Siflower firmware, you will need an Ubuntu 18.04 system.

Install the required dependencies:

```bash
sudo apt install make gcc g++ device-tree-compiler bc libncurses-dev perl-modules-5.26 patch gawk unzip python git
```

Get source code

```bash
git clone https://github.com/BPI-SINOVOIP/BPI-WiFi5-Siflower
```

----------

### **Build**

Build U-Boot

Navigate to the U-Boot directory and run the build script:

```bash
cd ./BPI-WiFi5-Siflower/uboot

./make.sh sfa28_ac28
```

Build OpenWrt

Navigate to the OpenWrt directory and run the build script:

```bash
cd ./BPI-WiFi5-Siflower/openwrt-18.06

./make.sh a28_bpi
```

----------

### **Flash**


The target firmware image will be in the ./ directory. Flash it to your device via the web interface. For detailed instructions on how to flash the image, refer to the [BPI-WiFi5-Siflower Wiki](https://docs.banana-pi.org/en/BPI-WiFi5_Router/GettingStarted_BPI-WiFi5_Router#_upgrade_firmware) for how to flash the image.