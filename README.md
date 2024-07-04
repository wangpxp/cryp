### 依赖库
git submodule add https://github.com/yhirose/cpp-httplib.git

### 编译
mkdir build

cd build

cmake ..

make


### 运行
./crypto_server


### 测试
curl -X POST http://localhost:8080/authorize -d '{"token": "my_token"}' -H "Content-Type: application/json"