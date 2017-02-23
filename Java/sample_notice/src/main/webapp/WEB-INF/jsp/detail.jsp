<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib uri="http://www.springframework.org/tags" prefix="spring" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
</head>
<body>
<h1><!-- spring:message code="message.detail"/ -->Detail</h1>
<form method="POST" action="save">
<input type="hidden" name="seq" value="${notice.getSeq()}">
번호 : <input type="text" value="${notice.getSeq() + 1}" readonly>
제목 : <input type="text" name="title" value="${notice.getTitle()}"> 
작성자 : <input type="text" name="userId" value="${notice.getUserId()}" readonly> <br>
내용 : <textarea name="content">${notice.getContent()}</textarea>

<input type="submit" value="수정">
</form>
</body>
</html>