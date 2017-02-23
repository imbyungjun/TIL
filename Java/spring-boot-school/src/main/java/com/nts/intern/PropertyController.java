package com.nts.intern;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class PropertyController {
	@Value("${application.message}")
	private String message = "Hello";
	
	@ResponseBody
	@RequestMapping("message")
	public String message() {
		return message;
	}
	
	
	
	
}
