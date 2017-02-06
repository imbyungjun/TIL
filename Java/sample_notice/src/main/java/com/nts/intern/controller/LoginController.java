package com.nts.intern.controller;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import com.nts.intern.dao.UserDao;
import com.nts.intern.vo.User;

@Controller
@RequestMapping("login")
public class LoginController {
	private static final Logger logger = LoggerFactory.getLogger(LoginController.class);

	@Autowired
	UserDao userDao;

	@RequestMapping(value = "form")
	public String loginForm() {
		return "loginForm";
	}

	@RequestMapping(value = "submit", method = { RequestMethod.POST })
	public String login(HttpServletRequest request, HttpServletResponse response, User user) {

		// login 여기서! 쿠키를 세팅해줌!
		if (userDao.exists(user)) {
			logger.info("Admin 확인되었음.");
			Cookie cookie = new Cookie("noticeAdmin", "admin");
			cookie.setMaxAge(30);
			cookie.setPath("/");		/* 이렇게 해야 쿠키의 적용범위가 ㅠㅠㅠㅠㅠㅠ */
			response.addCookie(cookie);

			return "redirect:/notice/list";
		}
		
		logger.info("로그인 실패");
		Cookie cookie = new Cookie("noticeAdmin", null);
		cookie.setPath("/");
		response.addCookie(cookie);
		return "redirect:/login/form";
	}
}
