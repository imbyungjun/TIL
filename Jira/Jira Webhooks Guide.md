# Webhooks
웹훅은 사용자가 정의한 HTTP 콜백입니다. 웹훅을 통해서 Jira에서 발생한 특정 이벤트들을 당신의 애플리케이션에 알릴 수 있습니다. 웹훅을 이용하면 변경 사항을 확인하기 위해서 지속적으로 polling 할 필요가 없습니다.

## Components
* Name : 웹훅의 이름
* URL : 콜백을 받을 주소
* Scope : 웹훅이 수신할 범위 (모든 이슈 / JQL로 명시된 특정 이슈들)
* Events : 수신할 이벤트 종류

## Registering a webhook
웹훅을 등록하는 방법은 두 가지가 있습니다. 

* Jira administartion console 
* Jira REST API (user must have admin permission)

요청에 따라서 웹앱에서 새로운 Jira 웹훅을 자동으로 등록하는 경우가 아니라면, 굳이 REST API를 사용할 일은 없을 것 같습니다.

## Configuring a webhook
### Registering events for a webhook
Jira 웹훅에서 사용 가능한 모든 이벤트들의 목록은 [도큐먼트](https://developer.atlassian.com/server/jira/platform/webhooks/)에서 확인할 수 있습니다. Response의 `webhookEvent` 필드로 이벤트 이름을 받을 수 있습니다.

### Choosing events for your webhook
어떤 이벤트를 감지해야할지 모르겠다면, 단순하게 모든 이벤트를 수신하도록 설정하고 추후에 변경하는것도 좋은 방법입니다.

### Restricting your evetns to a subset of issue via JQL
웹훅 설정에 JQL을 명시하여 수신할 이벤트를 특정 이슈에 한정지을 수 있습니다.

### Variable substitution in the webhook URL
웹훅을 수신할 URL에 아래와 같은 변수를 사용할 수 있습니다. 이는 path variable로 사용되기에 적합합니다.

* `${board.id}`
* `${issue.id}`
* `${issue.key}` 
* `${mergedVersion.id}` 
* `${modifiedUser.key}` 
* `${modifiedUser.name}` 
* `${project.id}` 
* `${project.key}` 
* `${sprint.id}` 
* `${version.id}`

예를들어 `${issue.key}` 변수는 아래와 같은 URL에 사용될 수 있습니다.

```
http://jira.example/webhook/${issue.key}
```
위와같은 콜백 URL을 설정한 뒤 이슈키가 **AAA-1**인 이슈에서 변경이 발생한 경우 아래와 같은 주소로 요청이 전달됩니다.

```
http://jira.example/webhook/AAA-1
```

## Adding a webhook as a post function to a workflow

## Executing a webhook
웹훅은 별도의 사용자 컨텍스트가 없이 실행됩니다. 일괄적으로 모든 웹훅 콜백은 query param으로 admin의 user_id와 user_key를 전달합니다.

기본적으로, 웹훅은 콜백의 body에 JSON 데이터를 포함시킵니다. JSON body가 필요 없는 경우 웹훅 설정에서 **Exclude body** 옵션을 체크하면 됩니다.

모든 콜백은 `webhookEvent` ID와 `timestamp`, 그리고 이벤트와 관련된 정보들을 포함합니다. 콜백들은 이벤트 타입에 따라서 추가적인 정보를 가질 수 있습니다. 


웹훅이 정상적으로 유발된 경우 응답 코드 200을 전달합니다. 이외의 응답 코드는 비정상적인 경우입니다.

### Callback Body Example

```
{
    "timestamp"
    "event"
    "user": {
               ...
    },
    "issue": {
               ...
    },
    "changelog" : {
               ...
    },
    "comment" : {
               ...
    }
}
```

Fields | Contents
-------|--------
Issue | * Jira REST API를 통해서 이슈를 얻었을 때와 같은 결과를 얻습니다. (no expand) <br>* 이슈는 웹훅 POST에 언제나 포함됩니다.
User | * Jira REST API를 통해서 사용자를 얻을 때와 같은 결과를 얻습니다. (without active, timezone, or groups) <br>* 사용자에 대한 더 자세한 정보를 얻기 위해서는 Jira REST API에 username을 통한 질의를 해야합니다. <br>* 사용자는 웹훅 POST에 언제나 포함됩니다.
Changelog | * 변경 사항에 대한 배열을 얻습니다. <br> * 각각의 배열 요소은 한 가지 필드의 변경 사항을 나타냅니다. <br>* 변경 사항은 issue_updated 이벤트에서만 제공됩니다.
Comment | * Jira REST API를 통해서 댓글을 얻었을 때와 같은 결과를 얻습니다. <br>* 댓글은 댓글과 관련한 변경이 있을 경우에만 제공됩니다.

```
{
    "id": 2,
    "timestamp": 1525698237764,
    "issue": {
        "id":"99291",
        "self":"https://jira.atlassian.com/rest/api/2/issue/99291",
        "key":"JRA-20002",
        "fields":{
            "summary":"I feel the need for speed",
            "created":"2009-12-16T23:46:10.612-0600",
            "description":"Make the issue nav load 10x faster",
            "labels":["UI", "dialogue", "move"],
            "priority": "Minor"
        }
    },
    "user": {
        "self":"https://jira.atlassian.com/rest/api/2/user?username=brollins",
        "name":"brollins",
        "key":"brollins",
        "emailAddress":"bryansemail at atlassian dot com",
        "avatarUrls":{
            "16x16":"https://jira.atlassian.com/secure/useravatar?size=small&avatarId=10605",
            "48x48":"https://jira.atlassian.com/secure/useravatar?avatarId=10605"
        },
        "displayName":"Bryan Rollins [Atlassian]",
        "active" : "true"
    },
    "changelog": {
        "items": [
            {
                "toString": "A new summary.",
                "to": null,
                "fromString": "What is going on here?????",
                "from": null,
                "fieldtype": "jira",
                "field": "summary"
            },
            {
                "toString": "New Feature",
                "to": "2",
                "fromString": "Improvement",
                "from": "4",
                "fieldtype": "jira",
                "field": "issuetype"
            }
        ],
        "id": 10124
    },
    "comment" : {
        "self":"https://jira.atlassian.com/rest/api/2/issue/10148/comment/252789",
        "id":"252789",
        "author":{
            "self":"https://jira.atlassian.com/rest/api/2/user?username=brollins",
            "name":"brollins",
            "emailAddress":"bryansemail@atlassian.com",
            "avatarUrls":{
                "16x16":"https://jira.atlassian.com/secure/useravatar?size=small&avatarId=10605",
                "48x48":"https://jira.atlassian.com/secure/useravatar?avatarId=10605"
            },
            "displayName":"Bryan Rollins [Atlassian]",
            "active":true
        },
        "body":"Just in time for AtlasCamp!",
        "updateAuthor":{
            "self":"https://jira.atlassian.com/rest/api/2/user?username=brollins",
            "name":"brollins",
            "emailAddress":"brollins@atlassian.com",
            "avatarUrls":{
                "16x16":"https://jira.atlassian.com/secure/useravatar?size=small&avatarId=10605",
                "48x48":"https://jira.atlassian.com/secure/useravatar?avatarId=10605"
            },
            "displayName":"Bryan Rollins [Atlassian]",
            "active":true
        },
        "created":"2011-06-07T10:31:26.805-0500",
        "updated":"2011-06-07T10:31:26.805-0500"
    },  
    "webhookEvent": "jira:issue_updated"
}
```

## Reference
https://developer.atlassian.com/server/jira/platform/webhooks/
