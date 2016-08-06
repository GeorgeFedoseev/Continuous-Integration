# CI intergration proj for MPD Root

## INSTALLATION AND TROUBLESHOOTING  

SETUP OF RUNNER:  

1) install docker  
  apt-get install docker.io - old ver (works good); see docker site for newer ver  

2) install gitlab-ci-multi-runner (instructions in off repo)  

3) connect runner to coordinator via command: gitlab-runner register (and follow instructions)  
  user "shell" mode  

4) edit visudo via command: visudo  
  add to the end of the file: gitlab-runner ALL=(ALL) NOPASSWD: ALL  
  save file and exit  
  (this allows executing sudo commands without asking for password for runner)  

5) in coordinator machine - in GitLab web interface set runner to run particular proj  

NOW you can user runner  

additional software  

6) htop - monitor activity, process manager  
7) dstat - log cpu,mem,nwk usage  


TROUBLES  

1) symptm: build output hangs and build never ends; runner logs 400 Bad Request err (when submitting log to coordinator)  
   SOLUTION:   
     make sure /tmp partition size if enough for build log outputs  
     sometimes its 1MB and it's not enougth for long build logs  
     TO MAKE THIS PARTITION LARGER (100MB) exec commands:  
       sudo umount /tmp  
       sudo mount -t tmpfs -o size=104857600,mode=1777 overflow /tmp  
  


