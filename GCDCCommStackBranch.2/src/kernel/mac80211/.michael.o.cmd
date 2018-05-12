cmd_/home/its/Desktop/lab411_GCDC-master/GCDCCommStackBranch/src/kernel/mac80211/michael.o := gcc -Wp,-MD,/home/its/Desktop/lab411_GCDC-master/GCDCCommStackBranch/src/kernel/mac80211/.michael.o.d  -nostdinc -isystem /usr/lib/gcc/i486-linux-gnu/4.4.3/include -Iinclude  -I/usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include -include include/linux/autoconf.h -D__KERNEL__ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -m32 -msoft-float -mregparm=3 -freg-struct-return -mpreferred-stack-boundary=2 -march=i586 -mtune=generic -Wa,-mtune=generic32 -ffreestanding -fstack-protector -fstack-protector-all -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -Wframe-larger-than=1024 -fno-omit-frame-pointer -fno-optimize-sibling-calls -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fno-dwarf2-cfi-asm -D__CHECK_ENDIAN__  -DMODULE -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(michael)"  -D"KBUILD_MODNAME=KBUILD_STR(mac80211)"  -c -o /home/its/Desktop/lab411_GCDC-master/GCDCCommStackBranch/src/kernel/mac80211/.tmp_michael.o /home/its/Desktop/lab411_GCDC-master/GCDCCommStackBranch/src/kernel/mac80211/michael.c

deps_/home/its/Desktop/lab411_GCDC-master/GCDCCommStackBranch/src/kernel/mac80211/michael.o := \
  /home/its/Desktop/lab411_GCDC-master/GCDCCommStackBranch/src/kernel/mac80211/michael.c \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/types.h \
    $(wildcard include/config/x86/64.h) \
    $(wildcard include/config/highmem64g.h) \
  include/asm-generic/int-ll64.h \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/posix_types.h \
    $(wildcard include/config/x86/32.h) \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/posix_types_32.h \
  include/linux/bitops.h \
    $(wildcard include/config/generic/find/first/bit.h) \
    $(wildcard include/config/generic/find/last/bit.h) \
    $(wildcard include/config/generic/find/next/bit.h) \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/bitops.h \
    $(wildcard include/config/x86/cmov.h) \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/alternative.h \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/paravirt.h) \
  include/linux/stringify.h \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/asm.h \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/cpufeature.h \
    $(wildcard include/config/x86/invlpg.h) \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/required-features.h \
    $(wildcard include/config/x86/minimum/cpu/family.h) \
    $(wildcard include/config/math/emulation.h) \
    $(wildcard include/config/x86/pae.h) \
    $(wildcard include/config/x86/cmpxchg64.h) \
    $(wildcard include/config/x86/use/3dnow.h) \
    $(wildcard include/config/x86/p6/nop.h) \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/ext2-non-atomic.h \
  include/asm-generic/bitops/le.h \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/swab.h \
    $(wildcard include/config/x86/bswap.h) \
  include/linux/byteorder/generic.h \
  include/asm-generic/bitops/minix.h \
  include/linux/ieee80211.h \
    $(wildcard include/config/len.h) \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/unaligned.h \
  include/linux/unaligned/access_ok.h \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /usr/lib/gcc/i486-linux-gnu/4.4.3/include/stdarg.h \
  include/linux/linkage.h \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/linkage.h \
    $(wildcard include/config/x86/alignment/16.h) \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/typecheck.h \
  include/linux/ratelimit.h \
  include/linux/param.h \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  include/linux/dynamic_debug.h \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /usr/src/linux-headers-2.6.31-020631-generic/arch/x86/include/asm/div64.h \
  include/linux/unaligned/generic.h \
  /home/its/Desktop/lab411_GCDC-master/GCDCCommStackBranch/src/kernel/mac80211/michael.h \

/home/its/Desktop/lab411_GCDC-master/GCDCCommStackBranch/src/kernel/mac80211/michael.o: $(deps_/home/its/Desktop/lab411_GCDC-master/GCDCCommStackBranch/src/kernel/mac80211/michael.o)

$(deps_/home/its/Desktop/lab411_GCDC-master/GCDCCommStackBranch/src/kernel/mac80211/michael.o):
