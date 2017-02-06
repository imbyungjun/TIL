SET DATABASE SQL SYNTAX MYS TRUE;
 
CREATE TABLE IF NOT EXISTS user ( 
 id varchar(40) primary key,
 passwd varchar(40) not null
);
 
CREATE TABLE IF NOT EXISTS notice ( 
 seq integer not null IDENTITY,
 title varchar(100) not null,
 content varchar(300) not null,
 userId varchar(40) not null
);
 
INSERT INTO user (id, passwd) VALUES ('admin', '1234');
 
INSERT INTO notice (title, content, userId) VALUES ('유승옥·정아름·이연·예정화…머슬글래머가 뜬다', '지난 23일 방송된 JTBC ‘썰전’에서는 ‘머슬글래머’를 놓고 예능심판자 김구라 강용석 박지윤 허지웅 이윤석이 대화를 나눴다. 김구라는 “예전에 여성들은 소녀시대 수영 씨 같은 다리를 갖고 싶어하지 않았냐”면서 이제는 달라진 여성들의 워너비 몸매를 꼽았다.', 'admin');
INSERT INTO notice (title, content, userId) VALUES ('송유빈 국민남동생 이승기 선배님이 롤모델(인터뷰)', '가수 송유빈(17)에겐 풋풋하고 신선한 느낌이 감돌았다. 친구들과 노래방에 가면 자의반, 타의반 마이크를 놓을 수 없었다는 송유빈은 친구들의 열띤 환호와 칭찬에 가수의 꿈을 꾸게 됐다. 보컬학원 선생님의 추천으로 지원한 케이블채널 엠넷 슈퍼스타K6(이하 슈스케6)는 송유빈을 조금 더 빨리 꿈으로 인도하는 매개체가 됐다.', 'admin');
INSERT INTO notice (title, content, userId) VALUES ('원조 체조요정 신수지, 댄싱9 출격…이지은과 호흡', '신수지는 현재 체조선수를 은퇴한 후 방송인으로 활동 중이다. 최근에는 MBC ‘천생연분 리턴즈’ 등을 통해 예능감을 뽐내고 있다, 댄스 프로그램인 ‘댄싱9’에서 어떤 모습을 보여주게 될지 기대를 모으고 있다.', 'admin');
INSERT INTO notice (title, content, userId) VALUES ('어벤져스2, 첫날 62만 동원…역대 외화 오프닝 1위', '영진위 영화관입장권 통합전산망에 따르면, 어벤져스2는 지난 23일 62만 769명을 동원했다. 박스오피스 1위다. 유료 시사회 관객수를 포함한 누적 관객수는 62만 2,470명이다.', 'admin');
INSERT INTO notice (title, content, userId) VALUES ('임성한 은퇴, 예정된 수순? 까마귀 날자 배 떨어졌나', '임성한 작가는 23일 매니지먼트사 명성당엔터테인먼트를 통해 은퇴 의사를 밝혔다. 열 작품을 하면 은퇴를 할 계획이었기에 이번 MBC 일일드라마 ‘압구정백야’가 마지막 작품이라는 것.', 'admin');
INSERT INTO notice (title, content, userId) VALUES ('송강호·김지운·최재원 ‘밀정’, 8월 촬영 시작', '배우 송강호와 김지운 감독 그리고 1000만 관객을 모은 영화 ‘변호인’의 제작자 최재원 대표가 최근 자주 만나 작품에 관한 논의를 하고 있다. 연기와 연출, 제작까지 영화에 관한 각 분야를 대표하는 흥행 ‘빅 맨’들이 다시 손을 잡을지 관심이 집중되고 있다.', 'admin');
INSERT INTO notice (title, content, userId) VALUES ('슈퍼맨 갑질 논란 사과에 체험관 측 "아량 베푼 KBS에 감사"', '[엑스포츠뉴스=김유진 기자] 슈퍼맨이 돌아왔다(이하 슈퍼맨)의 장소 섭외를 놓고 불거진 갑질논란 속에 KBS측이 사과의 뜻을 전한 가운데, 체험관 측이 이에 대한 입장을 전했다.', 'admin');
INSERT INTO notice (title, content, userId) VALUES ('소름고음 울산나얼 저격수, 2키 올린 바람기억', '23일 밤 9시 40분 방송된 Mnet 대반전 음악추리쇼 "너의 목소리가 보여"에서는 노을 강균성과 전우성이 얼굴만 보고 실력자인지 음치인지를 가리는 모습이 그려졌다.', 'admin');
INSERT INTO notice (title, content, userId) VALUES ('어벤져스2 크리스 에반스·제레미 레너, 여성비하 발언 공식사과', '24일 로이터 통신 보도에 따르면 영화 어벤져스:에이지 오브 울트론의 크리스 에반스와 제레미 레너가 스칼렛 요한슨이 연기한 블랙 위도우에 대해 "난잡한 계집(slut)", "매춘부"(whore)라고 표현한 것에 대해 사과의 뜻을 전했다.', 'admin');
INSERT INTO notice (title, content, userId) VALUES ('깝스 황제성 성대 엄친아? 개그에 학벌이 필요한가요?', '어눌한 한국말과 눈을 부라리며 째려보는 살기어린 눈빛, 하지만 그의 한마디 한마디에 객석은 그야말로 웃음바다다. 5분 내외의 짧은 코너지만 "하준수이~"부터 "애미야~" "할머니가 한국 사람입니다" 등 유행어를 탄생시키며 화제의 중심에 선 인물, 황제성(33)이 바로 그 주인공이다.', 'admin');