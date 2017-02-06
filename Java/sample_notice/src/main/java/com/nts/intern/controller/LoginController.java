package com.nts.intern.controller;

import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.cookie;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller
@RequestMapping("login")
public class LoginController {
	private static final Logger logger = LoggerFactory.getLogger(LoginController.class);
	
	@RequestMapping(value = "form")
	public String loginForm() {
		return "loginForm";
	}
	
	@RequestMapping(value = "submit", method = { RequestMethod.POST })
	public String login(HttpServletRequest request, HttpServletResponse response) {
		
		logger.info("Login submit~");
		
		// login 여기서! 쿠키를 세팅해줌!
		Cookie cookie = new Cookie("noticeAdmin", "admin");
		response.addCookie(cookie);
		
		return "redirect:/notice/list";
	}
}
