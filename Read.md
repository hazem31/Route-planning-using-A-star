# Startup sequence


```plantuml
@startuml
start
:Boot Manager startup;
:Boot Manager Main;
:Application startup;
:Application Main;
:EcuM StartPreOs Sequence;
:Start OS;
:EcuM StartPostOs Sequence;
:Rte Start;
stop
@enduml
```