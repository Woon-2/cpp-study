# Jira Issue를 Git과 연동하기
`Jira` `Issue`에 연관된 `Git` `Branch`와 `Git` `Commit`을 표시할 수 있습니다.   

- `Jira` `Issue`가 `Git` `Commit`와 유기적으로 연동되어 업무 진척이 훨씬 잘 보일 것입니다.

  - `Jira`의 `Issue`는 해야 할 일들이 알기 쉽게 요약되어있죠.
  - `Git`의 `Commit`은 실제적이고, 구체적인 우리의 작업들입니다.
  - `Github`에서 `Commit History`를 보아도 일련의 `Commit`들이 어떤 목적인지 보이지 않습니다.
  - 해야 할 일이 요약된 `Issue`별로 그 실제 처리 작업인 `Commit`이 분류되어 보인다면,업무 진척이 한 눈에 들어오겠죠.

## Table of contents

- [Issue Key](#issue-key)
- [Jira Issue에 연관된 Git Branch 표시하기](#jira-issue에-연관된-git-branch-표시하기)
- [Jira Issue에 연관된 Git Commit 표시하기](#jira-issue에-연관된-git-commit-표시하기)
- [Reference](#reference)

## Issue Key

- `Jira`의 `Issue`들은 모두 독립적인 `Issue Key`라는 것을 갖고 있습니다.

  <div align="center"><image src="https://user-images.githubusercontent.com/73771162/194705954-e522d207-88ed-475e-be92-1446ad053c52.PNG"></image></div>

  - `Board`의 `Issue` `Card` 왼쪽 아래에 `Issue Key`가 표시되어 있습니다.

  <div align="center"><image src="https://user-images.githubusercontent.com/73771162/194706052-201b132e-3d44-4d60-9740-3094d616b061.PNG"></image></div>  

  - `Issue`를 클릭하면 나오는 세부 정보 창의 위쪽에 `Issue Key`가 표시되어 있습니다.

<div align="center"><image src="https://user-images.githubusercontent.com/73771162/194706247-bd6f4e85-3cb6-4ad7-93d0-44d840ba83c7.png"></div>
<div align="center"><image src="https://user-images.githubusercontent.com/73771162/194706248-3024f668-5b32-4d87-99f1-2ce0bf750261.png"></image></div>
<div align="center">source: Atlassian JIRA</div>

## Jira Issue에 연관된 Git Branch 표시하기

- `Git` `Branch`의 이름에 `Jira` `Issue Key`가 포함되면, 해당 `Git` `Branch`와 해당 `Jira` `Issue`가 연동됩니다.

  - 이름만 바꾸면 연동이 된다니, 쉽죠?
  - 예시 사진의 `Issue Key`는 `BUG-8`이니, 다음과 같은 이름들이 가능할 겁니다.
    
    - `BUG-8`
    - `BUG-8-1234`
    - `BUG-8-Documentation`
    - `BUG-8-Test`

- 눈치 채셨겠지만, `Jira` `Issue`와 `Git` `Branch`는 일대다관계입니다.   
  하나의 `Jira` `Issue`에 여러 `Git` `Branch`를 연동할 수 있지만,   
  하나의 `Git` `Branch`는 하나의 `Jira` `Issue`만 연동할 수 있습니다.

  - 사실, `Branch` 이름이 여러 `Issue Key`를 포함하도록 하면 가능할 수도 있습니다.   
    실험해보지 않았습니다.

## Jira Issue에 연관된 Git Commit 표시하기

<div align="center"><image src="https://user-images.githubusercontent.com/73771162/194706752-f71ef5b8-630e-47ee-aa39-fa41ae56df7b.png"></image></div>
<div align="center"><image src="https://user-images.githubusercontent.com/73771162/194706752-f71ef5b8-630e-47ee-aa39-fa41ae56df7b.png"></image></div>
<div align="center">source: Atlassian JIRA</div>

- `Git` `Commit Message`에 `Jira` `Issue Key`가 포함되면, 해당 `Git` `Commit`과 해당 `Jira` `Issue`가 연동됩니다.

  - 예시 사진처럼, `Issue Key`를 포함해서 여러분이 적고 싶은 `Commit Message`를 작성하시면 됩니다.

## Reference

[\[Atlassian JIRA\] 지라 클라우드(JIRA Cloud) 와 깃허브(github) 연동하기](https://www.lesstif.com/jira/jira-cloud-github-125305615.html)