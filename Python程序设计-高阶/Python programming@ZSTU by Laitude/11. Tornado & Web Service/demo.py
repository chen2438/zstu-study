import tornado.web
import tornado.ioloop
 
class IndexHandler(tornado.web.RequestHandler):
 
    def get(self, *args, **kwargs):
        self.write("Hello World<br> I love Python")

    def post(self, *args, **kwargs):
        self.write("Hello World\n I love Python")        
 
application = tornado.web.Application([
    (r'/index',IndexHandler),
])
 
if __name__ == "__main__":
    application.listen(8080) 
    tornado.ioloop.IOLoop.instance().start() #