<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <title>登录结果</title>
</head>
<body>
    <%
        // 获取用户输入的用户名和密码
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // 预定义的正确用户名和密码
        String correctUsername = "tom";
        String correctPassword = "123456";

        // 验证用户名和密码
        if (correctUsername.equals(username) && correctPassword.equals(password)) {
            out.println("<h2>欢迎，" + username + "!</h2>");
        } else {
            out.println("<h2>账号或密码有误，请重新输入。</h2>");
            out.println("<a href='index.jsp'>返回登录页面</a>");
        }
    %>
</body>
</html>