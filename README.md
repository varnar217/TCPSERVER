для сборки проекта нужно g++ client.cpp -o client -pthread
g++ server.cpp -o server -pthread а для запуска нужно прописать в директории ./server <port_number>
./client <client_name> <port_number> <period_seconds> тогда появится log файл с соотвествующими данными . 
