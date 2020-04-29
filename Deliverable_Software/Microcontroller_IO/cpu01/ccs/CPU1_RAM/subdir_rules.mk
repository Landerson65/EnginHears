################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --tmu_support=tmu0 --cla_support=cla1 --float_support=fpu32 --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/include" -g --define=CPU1 --display_error_number --diag_suppress=10063 --diag_warning=225 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xS_CodeStartBranch.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/source/F2837xS_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --tmu_support=tmu0 --cla_support=cla1 --float_support=fpu32 --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/include" -g --define=CPU1 --display_error_number --diag_suppress=10063 --diag_warning=225 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xS_DefaultISR.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/source/F2837xS_DefaultISR.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --tmu_support=tmu0 --cla_support=cla1 --float_support=fpu32 --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/include" -g --define=CPU1 --display_error_number --diag_suppress=10063 --diag_warning=225 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xS_GlobalVariableDefs.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/headers/source/F2837xS_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --tmu_support=tmu0 --cla_support=cla1 --float_support=fpu32 --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/include" -g --define=CPU1 --display_error_number --diag_suppress=10063 --diag_warning=225 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xS_Gpio.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/source/F2837xS_Gpio.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --tmu_support=tmu0 --cla_support=cla1 --float_support=fpu32 --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/include" -g --define=CPU1 --display_error_number --diag_suppress=10063 --diag_warning=225 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xS_PieCtrl.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/source/F2837xS_PieCtrl.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --tmu_support=tmu0 --cla_support=cla1 --float_support=fpu32 --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/include" -g --define=CPU1 --display_error_number --diag_suppress=10063 --diag_warning=225 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xS_PieVect.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/source/F2837xS_PieVect.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --tmu_support=tmu0 --cla_support=cla1 --float_support=fpu32 --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/include" -g --define=CPU1 --display_error_number --diag_suppress=10063 --diag_warning=225 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xS_SysCtrl.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/source/F2837xS_SysCtrl.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --tmu_support=tmu0 --cla_support=cla1 --float_support=fpu32 --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/include" -g --define=CPU1 --display_error_number --diag_suppress=10063 --diag_warning=225 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xS_usDelay.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/source/F2837xS_usDelay.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --tmu_support=tmu0 --cla_support=cla1 --float_support=fpu32 --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/include" -g --define=CPU1 --display_error_number --diag_suppress=10063 --diag_warning=225 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

watchdog_cpu01.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/examples/cpu1/watchdog/cpu01/watchdog_cpu01.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/bin/cl2000" -v28 -ml -mt --vcu_support=vcu2 --tmu_support=tmu0 --cla_support=cla1 --float_support=fpu32 --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-c2000_18.12.2.LTS/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2837xs/common/include" -g --define=CPU1 --display_error_number --diag_suppress=10063 --diag_warning=225 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


