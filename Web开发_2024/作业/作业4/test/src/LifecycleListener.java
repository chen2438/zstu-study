import jakarta.servlet.ServletContextEvent;
import jakarta.servlet.ServletContextListener;
import jakarta.servlet.http.HttpSessionEvent;
import jakarta.servlet.http.HttpSessionListener;
import jakarta.servlet.ServletRequestEvent;
import jakarta.servlet.ServletRequestListener;

public class LifecycleListener implements ServletContextListener, HttpSessionListener, ServletRequestListener {

    // 监听 ServletContext 的创建
    @Override
    public void contextInitialized(ServletContextEvent sce) {
        System.out.println("ServletContext initialized: " + sce.getServletContext().getContextPath());
    }

    // 监听 ServletContext 的销毁
    @Override
    public void contextDestroyed(ServletContextEvent sce) {
        System.out.println("ServletContext destroyed.");
    }

    // 监听 HttpSession 的创建
    @Override
    public void sessionCreated(HttpSessionEvent se) {
        System.out.println("HttpSession created: " + se.getSession().getId());
    }

    // 监听 HttpSession 的销毁
    @Override
    public void sessionDestroyed(HttpSessionEvent se) {
        System.out.println("HttpSession destroyed: " + se.getSession().getId());
    }

    // 监听 ServletRequest 的创建
    @Override
    public void requestInitialized(ServletRequestEvent sre) {
        System.out.println("ServletRequest initialized: " + sre.getServletRequest().getRemoteAddr());
    }

    // 监听 ServletRequest 的销毁
    @Override
    public void requestDestroyed(ServletRequestEvent sre) {
        System.out.println("ServletRequest destroyed.");
    }
}
