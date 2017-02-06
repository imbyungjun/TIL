package com.nts.intern.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.nts.intern.dao.NoticeRepository;
import com.nts.intern.vo.Notice;

@RestController
@RequestMapping("/notice")
public class NoticeRestController {
	@Autowired
	private NoticeRepository noticeRepository;
//	
//	@RequestMapping("json")
//	public List<Notice> getNoticeList() {
//		return noticeRepository.getNoticeList();
//	}
}
