package com.nts.intern.controller;

import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;

import com.nts.intern.annotation.AuthCheck;
import com.nts.intern.dao.NoticeRepository;
import com.nts.intern.vo.Notice;

@Controller
@RequestMapping("notice")
public class NoticeController {
	private static final Logger logger = LoggerFactory.getLogger(NoticeController.class);
	
	@Autowired
	private NoticeRepository noticeRepository;
	
	@RequestMapping(value = "list", method = { RequestMethod.GET })
	public String getNoticeList(Model model,
			@RequestParam(value = "page", required = false, defaultValue = "1") int page,
			@RequestParam(value = "count", required = false, defaultValue = "10") int count) {
	
		Map<String, Integer> args = new HashMap<>();
		args.put("offset", (page - 1) * count);
		args.put("count", count);
		
		model.addAttribute("noticeList", noticeRepository.getNoticeList(args));
		return "list";
	}
	
	@RequestMapping(value = "{seq}")
	public String getNotice(Model model,
			@PathVariable int seq) {
		
		model.addAttribute("notice", noticeRepository.getNotice(seq - 1));
		
		return "detail";
	}
	
	@RequestMapping(value = "form")
	public String addForm() {
		return "addForm";
	}
	
	@AuthCheck
	@RequestMapping(value = "save", method = { RequestMethod.POST })
	public String saveNotice(Notice notice) {
		
		logger.info(notice.getSeq() + notice.getTitle() + notice.getUserId() + notice.getContent());
		
		noticeRepository.saveNotice(notice);
		
		return "redirect:list";
	}
}
