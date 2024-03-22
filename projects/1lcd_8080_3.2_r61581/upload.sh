PROJECT_NAME=$(echo $(pwd) | tr "/" "\n" | tail -1)
# stm32_tooler <-> STM32_Programmer_CLI   
stm32_tooler -c port=SWD -el board/stldr/ART-Pi_W25Q64.stldr  -d output/$PROJECT_NAME.elf

#About pyocd openocd, I took a try to get failuar...