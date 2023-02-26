
//8a. Status code 200 means everything worked
//8b. If you remove the res.end, then it never returns the code

const http = require('http');
const path = require('path');
const PublicHandler = require('./routes/public.js');


const server = http.createServer((req, res) =>  {

    const url = new URL(req.url, `http://${req.headers.host}`);
    const pathname = url.pathname;

    let reqPath = req.url;
    
    const publicDirectory = path.join(__dirname, '..', 'public');
    console.log(`Public Handler: ${publicDirectory} \nPath: ${path}`)
    for(const [route, method] of Object.entries(routes)){
        if(pathname.includes(pathname)){
            if(req.method.toLowerCase() === "get" && method.get){
                return method.get(req, res);
            }else{
                console.log(`Method !== method \nreq.method: ${req.method} \nroute method: ${method}`);
                return res.writeHead(405).end();
            }
        }
    }

})
server.listen(8080);


const routes = {
    '/public/': PublicHandler
}


