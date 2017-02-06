<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib uri="http://www.springframework.org/tags" prefix="spring" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
</head>
<body>
<h1><!-- spring:message code="message.addForm"/-->Add Form</h1>
<form method="POST" action="save">
<input type="hidden" name="userId" value="admin">
제목 : <input type="text" name="title"> <br>
내용 : <textarea name="content">내용을 입력하세요.</textarea>
<input type="submit" value="저장">
</form>
</body>
</html>