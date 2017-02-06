<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
</head>
<body>
	<h1>Notice List</h1>
	<table>
		<tr>
			<th>번호</th>
			<th>제목</th>
			<th>작성자</th>
		</tr>
		<c:forEach var="notice" items="${noticeList}">
			<tr id="${notice.getSeq()}">
				<td>${notice.getSeq() + 1}</td>
				<td>
				<a href="${notice.getSeq() + 1}">${notice.getTitle()}</a>
				</td>
				<td>${notice.getUserId()}</td>
			</tr>
		</c:forEach>
	</table>
	
	<a href="form">신규 게시물 작성</a>
</body>
</html>