package com.nts.intern.controller;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.nts.intern.dao.NoticeRepository;
import com.nts.intern.vo.Notice;

@RestController
@RequestMapping("/notice/json")
public class NoticeRestController {
	@Autowired
	private NoticeRepository noticeRepository;
	
	@RequestMapping(value = "list", method = { RequestMethod.GET })
	public List<Notice> getNoticeList(
			@RequestParam(value = "page", required = false, defaultValue = "1") int page,
			@RequestParam(value = "count", required = false, defaultValue = "10") int count) {
		
		Map<String, Integer> args = new HashMap<>();
		args.put("offset", (page-1)*count);
		args.put("count", count);
		
		return noticeRepository.getNoticeList(args);
	}
	
	@RequestMapping(value = "{seq}")
	public Notice getNotice(Model model,
			@PathVariable int seq) {
		
		return noticeRepository.getNotice(seq - 1);
	}
	
}
