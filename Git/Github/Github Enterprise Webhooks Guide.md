# Github Webhooks Guide

## Webhooks
웹훅을 사용하면 Github에서 발생하는 특정 이벤트를 수신하는 Github Application을 만들 수 있습니다. Github에서 이벤트가 발생하면 HTTP POST payload를 웹훅에 설정된 URL로 전달하게 됩니다. 웹훅을 외부 이슈 트래커 업데이트하기, CI 빌드를 유발, 백업을 수행 등에 사용할 수 있습니다. 사실상 당신이 원하는 거의 모든것을 수행할 수 있습니다.  
웹훅은 Github Enterprise에서 설정 가능하고 특정 Organization 혹은 특정 repository에서 설정 가능합니다. 각각의 이벤트에 대하여 최대 250개의 웹훅을 등록할 수 있습니다.

## Events
웹훅을 설정할 때, 어떤 이벤트를 수신할지 설정할 수 있습니다. [모든 이벤트를 수신](#wildcard-event)할 수 도 있습니다. 특정 이벤트에 대해서만 수신하면 불필요한 HTTP 요청을 줄일 수 있으므로 유용할 것입니다. 수신되는 이벤트 목록은 언제든지 UI 혹은 API 호출을 통해 수정할 수 있습니다. 기본값으로, 웹훅은 `push` 이벤트에 대해서만 수신하도록 설정됩니다.  
각각의 이벤트는 organization/repository에서 발생할 수 있는 액션과 일치합니다. 예를 들어, `issue` 이벤트를 수신하도록 설정했다면 issue의 open, closed, labeled 등의 모든 활동에 대해서 이벤트를 수신하게 될 것입니다.  
사용할 수 있는 이벤트들은 [webhooks#events](https://developer.github.com/enterprise/2.14/webhooks/#events)에서 확인할 수 있습니다.

### Wildcard Event
모든 이벤트에 매칭되는 와일드 카드(`*`)를 제공합니다. 와일드 카드 이벤트를 추가할 경우, 기존에 존재하던 설정들을 모두 와일드 카드 설정으로 대체하게 됩니다. 그리고 모든 이벤트에 대해서 요청을 보내게 됩니다. 추후에 이벤트가 추가될 경우 해당 이벤트도 수신하게 될 것입니다.

## Payloads
각각의 이벤트 타입은 이벤트 정보에 따른 요청의 형식을 갖습니다. 모든 이벤트 요청에 대한 정보는 [the payloads for the Event types]()에 자세하게 정리되어 있습니다.

> 이벤트에 따라 발생하는 요청은 25MB 이하로 제한되어 있습니다. 만약 사이즈가 큰 요청을 발생시킨다면, 웹훅은 발동되지 않을 것입니다. 예를들어, `create` 이벤트에서 많은 브랜치들과 태그들을 한 번에 푸시할 경우 웹훅이 발동되지 않을 수 있습니다.

### Delivery Headers
웹훅에 설정된 URL로 전달되는 HTTP POST 요청은 몇가지 특별한 헤더를 포함합니다.

Header | Description
------|-------
`X-Github-Event` | 발동된 이벤트 타입의 이름
`X-Github-Delivery` | 전달을 확인할 수 있는 GUID
`X-Github-Enterprise-Version` | 요청을 보낸 Github Enterprise 인스턴스의 버전
`X-Github-Enterprise-Host` | 요청을 보낸 Github Enterprise 인스턴스의 호스트 이름
`X-Hub-Signature` | The HMAC hex digest of the response body. This header will be sent if the webhook is configured with a secret. The HMAC hex digest is generated using the sha1 hash function and the secret as the HMAC key.
Also, the User-Agent for the requests will have the prefix GitHub-Hookshot/.

### Example Delivery
```
POST /payload HTTP/1.1
Host: localhost:4567
X-Github-Delivery: 72d3162e-cc78-11e3-81ab-4c9367dc0958
X-GitHub-Enterprise-Version: 2.15.0
X-GitHub-Enterprise-Host: example.com
X-Hub-Signature: sha1=7d38cdd689735b008b3c702edd92eea23791c5f6
User-Agent: GitHub-Hookshot/044aadd
Content-Type: application/json
Content-Length: 6615
X-GitHub-Event: issues
{
  "action": "opened",
  "issue": {
    "url": "http(s)://[hostname]/api/v3/repos/octocat/Hello-World/issues/1347",
    "number": 1347,
    ...
  },
  "repository" : {
    "id": 1296269,
    "full_name": "octocat/Hello-World",
    "owner": {
      "login": "octocat",
      "id": 1,
      ...
    },
    ...
  },
  "sender": {
    "login": "octocat",
    "id": 1,
    ...
  }
}
```

## Ping Event
새로운 웹훅을 만들었을때,`ping` 이벤트를 통해서 웹훅이 제대로 설정되었는지 확인할 수 있습니다. 이 이벤트는 저장되지 않기 때문에 Events API를 통해서 다시 찾을 수 없습니다. [Ping endpoint](https://developer.github.com/enterprise/2.14/v3/repos/hooks/#ping-a-hook)에 접근하면 `ping` 이벤트를 발생시킬 수 있습니다.

### Ping Event Payload
Key | Value
----|------
zen | Github이 생성한 임의의 문자열
hook_id | ping 이벤트를 발생시킨 웹훅의 아이디
hook | [웹훅 설정](https://developer.github.com/enterprise/2.14/v3/repos/hooks/#get-single-hook)


## Reference
https://developer.github.com/enterprise/2.14/webhooks/
