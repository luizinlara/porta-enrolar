# 🛠️ Porta de enrolar
Automação para porta de enrolar 220v e 4 lampadas, nessa solução utilizei o ESP8266.

Utilizado um webservice no ESP, o qual retorna um HTML de interação para o usuário, para enviar os comandos, 
foi criado uma rota */post* que recebe um JSON de acordo com a interação do usuário.

Projeto realizado apenas para estudo de novas stacks 😉

**Requisitos:**

* ESP8266
* Módulo de 4 rele
* Arduino IDE

**Instalação:**

**1º Passo :** Adicione a url de pacotes do ESP8266 em preferencias > Additional boards manager URLs
* http://arduino.esp8266.com/stable/package_esp8266com_index.json

**2º Passo :** Instale as bibliotecas
 * ESP8266WiFi
 * ESP8266WebServer

**3º Passo :** Altere as variáveis de conexão com a rede

* const char *ssid = "MEU_WIFI";
* const char *password = "SENHA_DO_WIFI";

**4º Passo :** Altere as urls do icones  no HTML(será o icone utilizado na tela inicia do celular) 
* \<link rel='apple-touch-icon' sizes='180x180' href='https://www.gardentec.com.br/apple-touch-icon.png'>
* \<link rel='icon' type='image/png' sizes='32x32' href='https://www.gardentec.com.br/favicon-32x32.png'>
* \<link rel='icon' type='image/png' sizes='16x16' href='https://www.gardentec.com.br/favicon-16x16.png'>

Observações: Utilizado em rede local, para não alterar o ip ao reiniciar os equipamentos, faça a reserva do ip MAC ADDRES no modem/roteador.
# Autor

[<img loading="lazy" src="https://avatars.githubusercontent.com/u/62263833?s=400&u=aca12fba393c657d421d37baf79a9a0f4ae46457&v=4" width=115><br><sub>Luis Lara</sub>](https://github.com/luizinlara)  |
| :---: |