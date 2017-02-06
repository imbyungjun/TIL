package com.nts.intern.dao;

import org.springframework.stereotype.Repository;

import com.nts.intern.vo.User;

@Repository
public interface UserDao {
	boolean exists(User user);
}
