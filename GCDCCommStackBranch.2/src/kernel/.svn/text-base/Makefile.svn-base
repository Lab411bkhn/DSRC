KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)/ath
	$(MAKE) -C $(KERNELDIR) M=$(PWD)/mac80211
	$(MAKE) -C $(KERNELDIR) M=$(PWD)/wireless

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)/ath clean
	$(MAKE) -C $(KERNELDIR) M=$(PWD)/mac80211 clean
	$(MAKE) -C $(KERNELDIR) M=$(PWD)/wireless clean

modules_prepare:
	$(MAKE) -C $(KERNELDIR) modules_prepare
