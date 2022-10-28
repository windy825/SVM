import cv2 as cv

cap = cv.VideoCapture(1)

number = 1
while 1:
    ret, img = cap.read()
    if not ret:
        print('Cant read camera')
        break

    cv.imshow('Fish-eye', img)

    if cv.waitKey(1) == ord('c'):
        img_captured = cv.imwrite(f'img_captured{number}.png', img)
        number += 1
        print('captured')
    elif cv.waitKey(1) == ord('q'):
        break

cap.release()
cv.destroyAllWindows()