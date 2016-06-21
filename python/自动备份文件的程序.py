import os 
import time 
source = ['"C:\\Users\Magneto_Wang\Documents\GitHub\Mr-Wang-s-Code"']
target_dir = 'C:\\Users\Magneto_Wang\Pictures'
target=target_dir+os.sep+time.strftime('%Y%m%d%H%M%S')+'.zip'
zip_command="zip -qr {0} {1}".format(target, ' '.join(source))
print(os.system(zip_command))
if os.system(zip_command) == 0:
    print('success',target)
else:
    print('backup')        
