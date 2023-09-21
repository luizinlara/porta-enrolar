#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "MEU_WIFI";
const char *password = "SENHA_WIFI";

const int rele1 = 2;
const int rele2 = 0;
const int rele3 = 4;
const int rele4 = 5;

const int rele5 = 14;//STOP
const int rele6 = 12;//SUBIR
const int rele7 = 13;//DESCER

bool porta_01_status = false;
bool porta_02_status = false;
bool porta_03_status = false;
bool porta_04_status = false;


ESP8266WebServer server(80);

void setup() {
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);

  pinMode(rele5, OUTPUT);
  pinMode(rele6, OUTPUT);
  pinMode(rele7, OUTPUT);
  
  digitalWrite(rele5, HIGH);
  digitalWrite(rele6, HIGH);
  digitalWrite(rele7, HIGH);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");
  server.on("/", HTTP_GET, handleRoot);
  server.on("/post", HTTP_POST, handlePost);
  server.on("/get", HTTP_GET, handleGet);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  const char* html = R"(
<!DOCTYPE html>
<html lang='en'>
<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>Controle</title>
    <link rel='apple-touch-icon' sizes='180x180' href='https://www.gardentec.com.br/apple-touch-icon.png'>
    <link rel='icon' type='image/png' sizes='32x32' href='https://www.gardentec.com.br/favicon-32x32.png'>
    <link rel='icon' type='image/png' sizes='16x16' href='https://www.gardentec.com.br/favicon-16x16.png'>
    <meta name='theme-color' content='#ffffff'>
    <style>
        html, body {
            background: #dadada;
            width: 98%;
        }

        .custom-radios div {
            display: inline-grid;
            grid-template-columns: auto auto;
            width: 90%;
            position: relative;
            margin-left: 30px;
        }

        .custom-radios input[type='checkbox'] {
            display: none;
        }

        .custom-radios input[type='checkbox'] + label {
            color: #333;
            font-family: Arial, sans-serif;
            font-size: 14px;
        }

        .custom-radios input[type='checkbox'] + label span {
            display: inline-block;
            width: 100%;
            height: 100px;
            vertical-align: middle;
            cursor: pointer;
            border: 10px solid #e5e5e5;
            box-shadow: 0 1px 1px 0 rgba(0, 0, 0, 0.33);
            background-repeat: no-repeat;
            background-position: center;
            text-align: center;
            line-height: 44px;
            margin-top: 10px;
            -webkit-border-radius: 10px;
            -moz-border-radius: 10px;
            border-radius: 10px;
        }

        .custom-radios input[type='checkbox'] + label span {
            background-color: #b9b9b9;
        }

        .custom-radios input[type='checkbox']:checked + label span {
            -webkit-box-shadow: 0px 0px 10px 0px rgb(248, 226, 157);
            -moz-box-shadow: 0px 0px 10px 0px rgb(248, 226, 157);
            box-shadow: 0px 0px 10px 0px rgb(248, 226, 157);
            opacity: 1;
            background: #FFFFFF;
            height: 100px;
            display: inline-block;
            position: relative;
        }

        .custom-radios input[type='checkbox']:checked + label span::before {
            content: '💡';
            position: absolute;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            font-size: 20px;
        }

        button {
            width: 49%;
            padding: 25px;
            margin-top: 25px;
            background: #331500;
            color: white;
            font-weight: 800;
            -webkit-border-radius: 10px;
            -moz-border-radius: 10px;
            border-radius: 10px;
            border: 4px solid #ffa750;
        }

        button:active {
            background-color: #b15f00; /* Cor de fundo alterada quando clicado */
        }

        .center {
            display: flex;
            justify-content: center;
            align-items: center;
        }

        .buttons {
            padding: 25px;
        }

    </style>
</head>
<body>
<div class='row'>
    <div class='custom-radios'>
        <div><h2>LAMPADA</h2></div>
        <div>
            <div>
                <input type='checkbox' id='l1' name='lampada' value='l1' >
                <label for='l1'><span></span></label>
            </div>
            <div>
                <input type='checkbox' id='l2' name='lampada' value='l2'>
                <label for='l2'><span></span></label>
            </div>
        </div>
        <br>
        <div>
            <div>
                <input type='checkbox' id='l3' name='lampada' value='l3'>
                <label for='l3'><span></span></label>
            </div>
            <div>
                <input type='checkbox' id='l4' name='lampada' value='l4'>
                <label for='l4'><span></span></label>
            </div>
        </div>
    </div>
</div>
<div class='buttons'>
    <div><h2>PORTA DE ENROLAR</h2></div>
    <div>
        <button type='button' onclick='porta("subir")'>SUBIR</button>
        <button type='button' onclick='porta("descer")'>DESCE</button>
    </div>
    <div class='center'>
        <button type='button' onclick='porta("stop")'>STOP</button>
    </div>
</div>
<script>
    function request(requestOptions, url) {
        return fetch(url, requestOptions)
            .then(response => {
                if (!response.ok) {
                    throw new Error(`Erro na requisição: ${response.status}`);
                }
                return response.json();
            })
            .then(responseData => {
                console.log('Resposta da requisição:', responseData);
                for (const key in responseData) {
                    if (document.getElementById(key)) {
                        document.getElementById(key).checked = (responseData[key]) ? true : false
                    }
                }
            })
            .catch(error => {
                console.error('Erro na requisição:', error);
            })
    }

    document.querySelectorAll('[name="lampada"]').forEach(lampada => {
        lampada.addEventListener('click', () => {
            request({
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({[lampada.value]: lampada.checked})
            }, './post')
        })
    })

    function porta(type) {
        request({
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({[type]: true})
        }, './post')
    }
</script>
</body>
</html>
)";

  server.send(200, "text/html", html);
}

void handlePost() {
  if (server.hasArg("plain")) {
    String text = server.arg("plain");
    Serial.println("Texto recebido via POST:");
    Serial.println(text);
    
      if(text.indexOf("{\"l1\":true}") > -1)
      {
        Serial.println("acionou rele true");
          porta_01_status = true;
          digitalWrite(rele1, LOW);
          Serial.println("Relé ligado");
          delay(1000);
      }
      if(text.indexOf("{\"l1\":false}") > -1)
      {
        Serial.println("acionou rele false");
        porta_01_status = false;
        digitalWrite(rele1, HIGH);
        Serial.println("Relé desligado");
        delay(1000);
      }



      if(text.indexOf("{\"l2\":true}") > -1)
      {
        Serial.println("acionou rele true");
          porta_02_status = true;
          digitalWrite(rele2, LOW);
          Serial.println("Relé ligado");
          delay(1000);
      }
      if(text.indexOf("{\"l2\":false}") > -1)
      {
        Serial.println("acionou rele false");
        porta_02_status = false;
        digitalWrite(rele2, HIGH);
        Serial.println("Relé desligado");
        delay(1000);
      }



      if(text.indexOf("{\"l3\":true}") > -1)
      {
        Serial.println("acionou rele true");
          porta_03_status = true;
          digitalWrite(rele3, LOW);
          Serial.println("Relé ligado");
          delay(1000);
      }
      if(text.indexOf("{\"l3\":false}") > -1)
      {
        Serial.println("acionou rele false");
        porta_03_status = false;
        digitalWrite(rele3, HIGH);
        Serial.println("Relé desligado");
        delay(1000);
      }



      if(text.indexOf("{\"l4\":true}") > -1)
      {
        Serial.println("acionou rele true");
          porta_04_status = true;
          digitalWrite(rele4, LOW);
          Serial.println("Relé ligado");
          delay(1000);
      }
      if(text.indexOf("{\"l4\":false}") > -1)
      {
        Serial.println("acionou rele false");
        porta_04_status = false;
        digitalWrite(rele4, HIGH);
        Serial.println("Relé desligado");
        delay(1000);
      }



      if(text.indexOf("{\"subir\":true}") > -1)
      {
        Serial.println("subir porta");
          digitalWrite(rele5, LOW);
          Serial.println("Relé ligado");
          delay(200);
          digitalWrite(rele5, HIGH);
      }
      if(text.indexOf("{\"descer\":true}") > -1)
      {
        Serial.println("descer porta");
        digitalWrite(rele6, LOW);
        delay(200);
        digitalWrite(rele6, HIGH);
      }
      if(text.indexOf("{\"stop\":true}") > -1)
      {
        Serial.println("stop porta");
        digitalWrite(rele7, LOW);
        delay(200);
        digitalWrite(rele7, HIGH);
      }
    handleGet();
  }
}
void handleGet() {
  	server.send(200, "Content-Type: application/json", "{\"l1\":"+ (String)porta_01_status +",\"l2\":"+ (String)porta_02_status +",\"l3\":"+ (String)porta_03_status +",\"l4\":"+ (String)porta_04_status +"}");
}
