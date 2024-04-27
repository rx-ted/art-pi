scons -j64
PROJECT_NAME=$(echo $(pwd) | tr "/" "
" | tail -1)
# stm32_tooler <-> STM32_Programmer_CLI   
# stm32_tooler -c port=SWD -el debug/stldr/ART-Pi_W25Q64.stldr  -d output/rtthread.elf -v -HardRst
stm32_tooler -c port=SWD -el debug/stldr/ART-Pi_W25Q64.stldr  -d output/$PROJECT_NAME.elf -v -HardRst