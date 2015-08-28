################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CXX_SRCS += \
src/FillRoot.cxx \
src/RawDatum.cxx \
src/TDRStream.cxx \
src/jurosort.cxx 

OBJS += \
libraries/FillRoot.o \
libraries/RawDatum.o \
libraries/TDRStream.o \
libraries/jurosort.o 

CXX_DEPS += \
libraries/FillRoot.d \
libraries/RawDatum.d \
libraries/TDRStream.d \
libraries/jurosort.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/%.o: src/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/opt/root/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


