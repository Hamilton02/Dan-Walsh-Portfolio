const fs = require('fs').promises;
const http = require('http');
const path = require('path');
const publicDirectory = path.join(__dirname, '..', 'public');

module.exports = {
    get:(req, res) => {
        try{
            let pathSplit = req.url.split('/').slice(1);
            console.log(`path split: ${pathSplit} \nReq.url: ${req.url}`);
            let filePath = path.join(publicDirectory, ...pathSplit);
            console.log(`file path: ${filePath}`);
            console.log("___________________\nReturns to module.exports");
            const typeArr= req.url.split('.');
            const type = typeArr.slice(typeArr.length - 1);
            console.log(type[0]);
            if(type[0] === 'html'){
                res.setHeader("Content-Type", 'text/html');
            }else if(type[0] === 'css'){
                res.setHeader("Content-Type", 'text/css');
            }else if(type[0] === 'js'){
                res.setHeader("Content-Type", 'text/javascript');
            }else if(type[0] === 'ico'){
                res.setHeader("Content-Type", 'image/ico');
            }else if(type[0] === 'svg'){
                res.setHeader("Content-Type", 'image/svg+xml');
            }
            
            return fs
            .readFile(filePath, "utf-8")
            .then((contents) => {
                res.statusCode = 200;
                res.write(contents);
                res.end();
            }) 
        }catch(err){
            console.log(err.code);
            if(err.code === "ENOENT"){
                res.writeHead(404);
                console.log(err.errno);
                res.end("404: NOT_FOUND");
            }else if(err.code === "EISDIR"){
                res.writeHead(500);
                console.log(err.errno);
                res.end("500: INTERNAL_SERVER_ERRO");
            }else{
                res.writeHead(500);
                res.end(res.end("500: INTERNAL_SERVER_ERRO"));
            }
        }
    }
}
