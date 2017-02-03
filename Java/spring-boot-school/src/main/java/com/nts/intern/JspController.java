package com.nts.intern;

import org.springframework.social.InternalServerErrorException;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class JspController {
	@RequestMapping("/")
	public String index() {
		return "index";
	}
	
	@RequestMapping("500") 
	public void e500() {
		throw new InternalServerErrorException(null, null);
	}
}
