# Robot-Tracking-System
Sistema embarcado para localização de robôs móveis dentro de ambientes controlados. A partir da leitura de QrCodes, o robô deve ser capaz de se localizar dentro de um ambiente e chegar ao seu destino.

# O que foi necessário para a raspberry

- Instalar Opencv (https://www.learnopencv.com/install-opencv-3-4-4-on-ubuntu-16-04/)
- Instalar zbar lib para leitura de QrCodes (https://github.com/ZBar/ZBar)
- Instalar QtCreator e libs do serialport
	- `sudo apt-get install libqt5serialport5`
	- `sudo apt-get install libqt5serialport5-dev`
- Instalar raspicam para C++ encontrado em (https://github.com/cedricve/raspicam)
- Mudança de captura de frames do opencv usando raspicam
- Mudança das flags de compilação no .pro do opencv, adição de flags para raspicam
