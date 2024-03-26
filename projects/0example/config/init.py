import os, sys
import commentjson as json


CURR = os.getcwd()
project_name = CURR.split("/")[-1]


openocd_config = {
    "cwd": "${workspaceRoot}/projects/" + project_name,
    "executable": "output/" + project_name + ".elf",
    "name": project_name,
    "request": "attach",
    "type": "cortex-debug",
    "servertype": "openocd",
    "configFiles": ["interface/stlink.cfg", "board/stm32h750b-disco.cfg"],
    "runToEntryPoint": "main",
    "svdFile": "debug/svd/STM32H750x.svd",
}


def debug():
    lanuch = os.path.join(CURR, "..", "..", ".vscode", "launch.json")
    if not os.path.exists(lanuch):
        print("Not find ", lanuch)
        return
    with open(lanuch) as f:
        lanuch_config: dict = json.load(f)
    if "configurations" in lanuch_config:
        project_size = len(lanuch_config["configurations"])

        flag = False
        for i in range(project_size):
            if lanuch_config["configurations"][i]["name"] == project_name:
                print("Aleardy wrote ", project_name)
                return
            else:
                flag = True
        if project_size == 0 or flag == True:
            lanuch_config["configurations"].append(openocd_config)

    with open(lanuch, "w", encoding="utf-8") as f:
        json.dump(lanuch_config, f)
    print("success to write ", lanuch)


def upload():
    s = """scons -j16
PROJECT_NAME=$(echo $(pwd) | tr "/" "\n" | tail -1)
# stm32_tooler <-> STM32_Programmer_CLI   
stm32_tooler -c port=SWD -el ../../debug/stldr/ART-Pi_W25Q64.stldr  -d output/$PROJECT_NAME.elf -v -HardRst"""
    with open("upload.sh", "w", encoding="utf-8") as f:
        f.write(s)
    print("success to write upload.sh\nPlease run sh upload.sh to download")


def main():
    debug()
    upload()


if __name__ == "__main__":
    main()
