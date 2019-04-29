# Robot-Tracking-System
Sistema embarcado para localização de robôs móveis dentro de ambientes controlados. A partir da leitura de QrCodes, o robô deve ser capaz de se localizar dentro de um ambiente e chegar ao seu destino.

# O que foi necessário para a raspberry

- Instalar Opencv, última versão 3.x (https://www.learnopencv.com/install-opencv-3-4-4-on-ubuntu-16-04/)
- Instalar zbar lib para leitura de QrCodes (https://github.com/ZBar/ZBar)
- Instalar QtCreator, principais libs e libs do serialport
	- `sudo apt-get install libqt5serialport5`
	- `sudo apt-get install libqt5serialport5-dev`
- Instalar raspicam para C++ encontrado em (https://github.com/cedricve/raspicam)
- Mudança de captura de frames do opencv usando raspicam
- Mudança das flags de compilação no .pro do opencv, adição de flags para raspicam
- Inicialização do executável em C++ pelo /etc/profile, usando link p/ variável que foi encontrado com `sudo ln -s caminho_arquivo`
- Utilização do script em python encontrado em https://github.com/TonyLHansen/raspberry-pi-safe-off-switch/, para desligamento da raspberry embarcada. Executado da mesma forma que o anterior.
