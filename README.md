# Robot-Tracking-System
Sistema embarcado para localização de robôs móveis dentro de ambientes controlados. A partir da leitura de QrCodes, o robô deve ser capaz de se localizar dentro de um ambiente e chegar ao seu destino.

# O que foi necessário para a raspberry

- Instalar Opencv
- Instalar zbar lib para leitura de QrCodes
- Instalar QtCreator e libs do serialport
- Instalar raspicam para C++ encontrado em (https://github.com/cedricve/raspicam)
- Mudança de captura de frames do opencv usando raspicam
- Mudança das flags de compilação no .pro do opencv
