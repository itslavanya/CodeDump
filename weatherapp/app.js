const express = require("express");
const https = require("https");
const app = express();
app.use(express.urlencoded({extended: true}));
app.get("/", function(req,res){
   res.sendFile(__dirname+"/index.html");

});
app.post("/",function(req,res){
    
const query = req.body.cityName;
const units = "metric";
const apiKey ="f3b9f0efed8965d8a42182d7ff5fd650";
const url = "https://api.openweathermap.org/data/2.5/weather?q="+query+"&units="+units+"&appid="+apiKey;
https.get(url,function(response){
  console.log(response.statusCode);
  response.on("data",function(data){
      const weatherData = JSON.parse(data);
      const temp = weatherData.main.temp;
      const desc = weatherData.weather[0].description;
      const icon = weatherData.weather[0].icon;
      const imageURL = "http://openweathermap.org/img/wn/"+icon+"@2x.png"
      res.write("<h1>The weather currently is "+desc+".</h1>");
      res.write("<h1>The temperature in "+query+" is "+temp+" degrees Celcius.</h1>");
      res.write("<img src="+imageURL+">");
      res.send();

  })
})
});




app.listen(3000,function(){
    console.log("Server is running on port 3000");
})