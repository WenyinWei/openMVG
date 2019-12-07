#include <fstream>
#include <iostream>

using namespace std;

// 进行图像拍摄。
// 返回码请按照此规范：0表示拍摄成功；1表示拍摄不成功。
int capture(string filename) {
  // Demo 只是生成简单的png文件（其实是txt），内容为文件名称。
  // 在实际使用中，请替换为图像拍摄逻辑。
  ofstream file;
  file.open(filename);
  file << filename.c_str();
  file.close();

  // 返回码：0表示拍摄成功；1表示拍摄不成功。
  return 0;
}

// Agent 在接收到拍摄命令后，执行以下调用：
// ./capture {filename}
// {filename}：图像存储名称
int main(int argc, char** argv) {
  // 这里忽略了命令行参数的检验，因为我相信大家都不会“作死”。

  // 获取图像文件名称。
  string filename = argv[1];
  // 进行图像拍摄，并存储为图片，使用返回码作为拍摄是否成功的依据。
  // ret：0表示拍摄成功；1表示拍摄不成功。
  int ret = capture(filename);

  return ret;
}
