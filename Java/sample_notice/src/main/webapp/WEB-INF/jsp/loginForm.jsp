<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib uri="http://www.springframework.org/tags" prefix="spring" %><!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
</head>
<body>
<H1><!-- spring:message code="message.loginForm"/ -->Login Form</H1>
<form method="POST" action="/login/submit">
ID : <input type="text" name="id"> <br>
PW : <input type="text" name="passwd"> <br>
<input type="submit" value="로그인">
</form>
</body>
</html>