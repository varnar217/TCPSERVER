from fastapi import FastAPI
from fastapi.responses import HTMLResponse

import socket

app = FastAPI()

@app.get("/")
def get_message():
    # Подключение к TCP серверу
    server_address = ('127.0.0.1', 3000)
    message = ""

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(server_address)
        data = s.recv(1024)
        message = data.decode("utf-8")
    print("\n message:\n",message)

    # Формирование HTML сообщения
    html_content = f"""
    <html>
    <head>
        <title>Привет, мир</title>
    </head>
    <body>
        <h1>{message}</h1>
    </body>
    </html>
    """

    return HTMLResponse(content=html_content, status_code=200)

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="localhost", port=8000)
