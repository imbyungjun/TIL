package com.nts.intern;

import javax.sql.DataSource;

import org.mybatis.spring.SqlSessionFactoryBean;
import org.mybatis.spring.annotation.MapperScan;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.core.io.support.PathMatchingResourcePatternResolver;
import org.springframework.jdbc.datasource.DataSourceTransactionManager;
import org.springframework.jdbc.datasource.embedded.EmbeddedDatabaseBuilder;
import org.springframework.jdbc.datasource.embedded.EmbeddedDatabaseType;
import org.springframework.transaction.annotation.EnableTransactionManagement;

@Configuration
@EnableTransactionManagement
@ComponentScan(basePackages = { "com.nts.intern" })
@MapperScan(basePackages = "com.nts.intern.dao")
public class PersistenceConfiguration {
	@Bean
	public DataSource dataSource() {
		return new EmbeddedDatabaseBuilder().addScript("classpath:notice_schema.sql")
				.setScriptEncoding("UTF-8")
				.setType(EmbeddedDatabaseType.HSQL).build();
	}

	@Bean
	public DataSourceTransactionManager mybatisTransaction(DataSource dataSource) {
		return new DataSourceTransactionManager(dataSource);
	}
	
	@Bean
	public SqlSessionFactoryBean sqlSessionFactoryBean(DataSource dataSource) throws Exception {
		SqlSessionFactoryBean sessionFactory = new SqlSessionFactoryBean();
		sessionFactory.setDataSource(dataSource);
		
		sessionFactory
		.setMapperLocations(new PathMatchingResourcePatternResolver()
				.getResources("classpath:mapper/*.xml"));
		
		return sessionFactory;
	}
}

