<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <title>登录界面</title>
</head>
<body>
    <h2>登录</h2>
    <form action="loginProcess.jsp" method="post">
        <label for="username">用户名：</label>
        <input type="text" id="username" name="username"><br><br>
        <label for="password">密码:</label>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="登录">
    </form>
</body>
</html>