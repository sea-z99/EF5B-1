################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPIO.c \
../HelloBye.c \
../Led.c \
../LedLib.c \
../OSC.c \
../SoftSpi.c \
../Work.c \
../config_set.c \
../main.c \
../music.c \
../music_led.c \
../new_music.c \
../timer.c 

OBJS += \
./GPIO.o \
./HelloBye.o \
./Led.o \
./LedLib.o \
./OSC.o \
./SoftSpi.o \
./Work.o \
./config_set.o \
./main.o \
./music.o \
./music_led.o \
./new_music.o \
./timer.o 

C_DEPS += \
./GPIO.dep \
./HelloBye.dep \
./Led.dep \
./LedLib.dep \
./OSC.dep \
./SoftSpi.dep \
./Work.dep \
./config_set.dep \
./main.dep \
./music.dep \
./music_led.dep \
./new_music.dep \
./timer.dep 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo '正在构建文件： $<'
	@echo '正在调用： C Compiler'
	kf8cc -c -pKF8A200GQS -I"E:\KungFuIDE\include" -I"C:\Users\Rick\Desktop\EF5B\EF5B程序\EF5B-1" -o"$@" "$<"
	@echo '已结束构建： $<'
	@echo ' '


