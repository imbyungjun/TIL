package com.nts.intern.interceptor;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.method.HandlerMethod;
import org.springframework.web.servlet.HandlerInterceptor;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.handler.HandlerInterceptorAdapter;

import com.nts.intern.annotation.AuthCheck;
import com.nts.intern.controller.NoticeController;

public class LoginCheckInterceptor implements HandlerInterceptor {
	private static final Logger logger = LoggerFactory.getLogger(LoginCheckInterceptor.class);

	@Override
	public boolean preHandle(HttpServletRequest req, HttpServletResponse res, Object handler) throws Exception {
		if (!(handler instanceof HandlerMethod)) {
			return true;
		}

		AuthCheck authCheck = ((HandlerMethod) handler).getMethodAnnotation(AuthCheck.class);
		
		if (authCheck == null) {
			return true;
		}
		
		Cookie[] cookies = req.getCookies();
		 
		for (Cookie c : cookies) {
			if (c.getName().equals("noticeAdmin") && c.getValue().equals("admin")) {
				logger.info("cookie : " + c.getName() + c.getValue());
				return true;
			}
		}
		
		res.sendRedirect("/login/form");
		return false;
	}

	@Override
	public void afterCompletion(HttpServletRequest arg0, HttpServletResponse arg1, Object arg2, Exception arg3)
			throws Exception {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void postHandle(HttpServletRequest arg0, HttpServletResponse arg1, Object arg2, ModelAndView arg3)
			throws Exception {
		// TODO Auto-generated method stub
		
	}
}
