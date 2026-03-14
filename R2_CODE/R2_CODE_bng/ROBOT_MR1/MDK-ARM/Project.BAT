SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Users\jukyn\AppData\Local\Microsoft\WindowsApps;%DASHLANE_DLL_DIR%
SET CPU_TYPE=STM32F407VETx
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Project
SET CPU_CLOCK=0x007A1200
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\stm32f4xx_it.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\system_stm32f4xx.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\project\startup_stm32f4xx._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\misc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\stm32f4xx_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\stm32f4xx_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\stm32f4xx_adc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\stm32f4xx_dma.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\stm32f4xx_exti.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\stm32f4xx_spi.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\stm32f4xx_tim.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\stm32f4xx_usart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\stm32f4xx_syscfg.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\croutine.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\list.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\queue.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\timers.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\port.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\heap_2.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\project\tasks.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Project\Project.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Project\Project.axf" --i32combined --output ".\Project\Project.hex"
