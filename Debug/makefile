################################################################################
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

-include $(C_DEPS)

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# 所有目标
all: EF5B-1.hex

# 工具调用
EF5B-1.hex: $(OBJS) $(USER_RELS)
	@echo '正在构建目标： $@'
	@echo '正在调用： C Linker Debug'
	kf8link_debug.exe -O3 KF8A200GQS_monitor.lib libkf8v4.lib KF8A200GQS.lib KF8_Touch_Fun.lib -s"E:/KungFuIDE/kfl/KF8A200GQS.kfl" -o "EF5B-1.hex" $(OBJS) $(USER_RELS) $(LIBS)
	@echo '已结束构建目标： $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# 其他目标
clean:
	-$(RM) $(OBJS)$(EXECUTABLES)$(C_DEPS) EF5B-1.hex
	-@echo ' '

post-build:
	-kf8exec_debug.exe EF5B-1
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
