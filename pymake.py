import subprocess
import sys
import datetime
import glob
import os

#test

cmd = 'g++ '
src = ['src/*.cpp']
include = ['-I/usr/include/mysql', '-Iincludes']
link = ['-L/usr/lib/mysl', '-lmysqlclient']
output = 'othello_exe.out'

for s in src:
    cmd += s + ' '
for i in include:
    cmd += i + ' '
for l in link:
    cmd += l + ' '
cmd += '-o ' + output


if len(sys.argv) == 1:
    subprocess.run(cmd, shell=True)
    subprocess.run(['./' + output])

elif len(sys.argv) == 2:
    if sys.argv[1].lower() == 'c':
        subprocess.run('python util/clean.py .out safety=false', shell=True)
        for x in glob.glob(os.path.abspath(os.getcwd() + '/logs/*.log')):
            f = open(x, 'w').close()

    elif sys.argv[1].lower() == 'm':
        subprocess.run(cmd, shell=True)

    elif sys.argv[1].lower() == 'r':
        subprocess.run(['./' + output])

    elif sys.argv[1].lower() == 'push':
        subprocess.run(['python', 'util/clean.py', '.out', 'safety=false'])
        subprocess.run(['git', 'add', '.'])
        subprocess.run(['git', 'commit', '-m', str(datetime.datetime.now())])
        subprocess.run(['git', 'push'])

    elif sys.argv[1].lower() == 'pull':
        subprocess.run(['git', 'pull'])

    elif sys.argv[1].lower() == 'install':
        subprocess.run('sudo yum install -y mysql-devel', shell=True)
        subprocess.run('sudo yum install -y mariadb mariadb-server', shell=True)
        subprocess.run('systemctl start mariadb', shell=True)
        subprocess.run('systemctl enable mariadb', shell=True)

        
        

    else:
        raise ValueError('Invalid Input: Not a valid command')
else:
    raise ValueError('Invalid Input: Too many commands')
