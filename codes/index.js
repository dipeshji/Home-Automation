const express = require('express');
const bodyparser = require('body-parser');
const fs =require('fs')
const app = express();
const https = require('https')
const PORT = process.env.PORT || 8443;
var HOST = process.env.HOST || '';
const mqtt = require('mqtt');
var client  = mqtt.connect('mqtt://brokersIP:1883');
app.use(bodyparser.json());

client.on('connect',()=>{
    console.log("MQTT connected");
    
})
const topic = 'light';

var options = {
        key: fs.readFileSync('ssl/privkey.pem'),
        ca: fs.readFileSync('ssl/fullchain.pem'),
        cert: fs.readFileSync('ssl/cert.pem')
    }
https.createServer(options, app).listen(PORT, HOST, null, function () {
    console.log('Server listening on port %d in %s mode', this.address().port)
})


app.post('/',(req,res)=>{
    console.log(req.body.queryResult.parameters);
    if(req.body.queryResult.parameters.status == 'on' && req.body.queryResult.parameters.device == 'light')
    {
        console.log("on");
        client.publish(topic,'1,4');
 console.log("Published")
        res.json({
        "fulfillmentText": "ok boss!! turning on light",
    "fulfillmentMessages": [
      {
        "text": {
          "text": [
            "ok boss!! turning on light"
          ]
        }
      }
    ],
})
    }
    else if(req.body.queryResult.parameters.status == 'off' && req.body.queryResult.parameters.device == 'light')
    {
        {
            console.log("off");
            client.publish(topic,'0,4');
            console.log("Published")
            res.json({
                "fulfillmentText": "ok boss!! turning on light",
                "fulfillmentMessages": [
                {
                    "text": {
                    "text": [
                        "ok boss!! turning off light"
                    ]
                    }
                }
                ],
            });
    }
}
else if(req.body.queryResult.parameters.status == 'lets' && req.body.queryResult.parameters.device == 'party')
{
    {
        console.log("party mode");
        client.publish(topic,'0,5');
        console.log("Published")
        res.json({
            "fulfillmentText": "ok boss!! lets party",
            "fulfillmentMessages": [
            {
                "text": {
                "text": [
                    "ok boss!! lets party"
                ]
                }
            }
            ],
        });
}
}
else if(req.body.queryResult.parameters.status == 'want' && req.body.queryResult.parameters.device == 'sleep')
{
    {
        console.log("party mode");
        client.publish(topic,'0,6');
        console.log("Published")
        res.json({
            "fulfillmentText": "ok boss!! you can sleep ",
            "fulfillmentMessages": [
            {
                "text": {
                "text": [
                    "ok boss!! you can sleep"
                ]
                }
            }
            ],
        });
}
}
})

        