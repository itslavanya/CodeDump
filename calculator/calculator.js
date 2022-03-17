const express = require("express");

const app = express();
app.use(express.urlencoded({extended:true}));
app.get("/",function(req,res){
    res.sendFile(__dirname+"/index.html");


});
app.post("/",function(req,res){
    var num1 = Number(req.body.num1);
    var num2 = Number(req.body.num2);
    var result = num1 + num2;

    res.send("The result of the calculation is "+result.toString());
});
app.get("/bmicalculator",function(req,res){
    res.sendFile(__dirname+"/bmiCalculator.html");
});
app.post("/bmicalculator",function(req,res){
    var height = Number(req.body.height);
    var weight = Number(req.body.weight);
    var n = weight/(height*height);
    res.send("Your BMI is "+n.toString());

})
app.listen(8080,function(){
    console.log("Server is running on port 3000.");
});