package com.nts.intern;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.util.StringUtils;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HelloController {
	private static final Logger logger = LoggerFactory.getLogger(HelloController.class);
	
	@Autowired
	private CustomerRepository customerRepository;
	
	@RequestMapping("hello")
	public String hello() {
		return "Hello Spring Boot!";
	}

	@RequestMapping(value = "customers", method = { RequestMethod.GET })
	public List<Customer> read(Customer customer) {
		
		if (!StringUtils.isEmpty(customer.getName())) {
			return customerRepository.findByName(customer.getName());
		}
		
		return customerRepository.findAll();
	}
	
	@RequestMapping(value = "customers", method = { RequestMethod.POST })
	public Customer add(Customer customer) {
		return customerRepository.save(customer);
	}
	
	@RequestMapping(value = "customers/{id}", method = { RequestMethod.GET })
	public Customer getCustomer(@PathVariable Long id) {
		return customerRepository.findOne(id);
	}
	
	@RequestMapping(value = "customers/{id}", method = { RequestMethod.PUT })
	public Customer update(@PathVariable Long id, Customer customer) {
		customer.setId(id);
		return customerRepository.save(customer);
	}
	
	@RequestMapping(value = "customers/{id}", method = { RequestMethod.DELETE })
	public void delete(@PathVariable Long id) {
		customerRepository.delete(id);
	}
}
