package com.nts.intern.dao;

import java.util.List;
import java.util.Map;

import org.springframework.stereotype.Repository;

import com.nts.intern.vo.Notice;

@Repository
public interface NoticeRepository {
	List<Notice> getNoticeList(Map<String, Integer> args);
	Notice getNotice(int seq);
	boolean saveNotice(Notice notice);
}
