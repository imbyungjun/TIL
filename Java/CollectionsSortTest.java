package demo.service;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import org.junit.Before;
import org.junit.Test;

import demo.vo.User;

public class CollectionsSortTest {
	List<User> userList;

	@Before
	public void setup() {		
		userList = new ArrayList<>();
		
		User user0 = new User();
		User user1 = new User();
		User user2 = new User();
		
		user0.setName("A");
		user1.setName("B");
		user2.setName("C");
		
		userList.add(user1);
		userList.add(user0);
		userList.add(user2);
	}
	
	@Test
	public void TestCollectionsSortNameAsc() {
		// given
		// when
		Collections.sort(userList, new NameAscCompare());
		
		// then
		userList.get(0).equals("A");
		userList.get(1).equals("B");
		userList.get(2).equals("C");
	}
	
	@Test
	public void TestCollectionsSortNameDesc() {
		// given
		// when
		Collections.sort(userList, new NameDescComapre());
		
		// then
		userList.get(0).equals("C");
		userList.get(1).equals("B");
		userList.get(2).equals("A");
	}
}

class NameAscCompare implements Comparator<User> {

	@Override
	public int compare(User o1, User o2) {
		return o1.getName().compareTo(o2.getName());
	}
	
}

class NameDescComapre implements Comparator<User> {

	@Override
	public int compare(User o1, User o2) {
		return o2.getName().compareTo(o1.getName());
	}
	
}
