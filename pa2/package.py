import os
import zipfile

# 只包含 src/ 下的源码文件和 CMakeLists.txt
INCLUDE_DIRS = ["src"]
INCLUDE_FILES = ["CMakeLists.txt"]

def zip_project(zip_name="project.zip"):
    with zipfile.ZipFile(zip_name, "w", zipfile.ZIP_DEFLATED) as zipf:
        # 打包目录
        for directory in INCLUDE_DIRS:
            for root, dirs, files in os.walk(directory):
                # 排除隐藏目录
                dirs[:] = [d for d in dirs if not d.startswith(".")]
                for file in files:
                    if file.startswith("."):
                        continue
                    file_path = os.path.join(root, file)
                    arcname = os.path.relpath(file_path, start=os.path.dirname(directory))
                    zipf.write(file_path, arcname)

        # 打包单独文件
        for file in INCLUDE_FILES:
            if os.path.isfile(file):
                zipf.write(file, file)

    print(f"已生成压缩包：{zip_name}")

if __name__ == "__main__":
    zip_project()
