package service;

import exception.PersistentException;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class ServiceInvocationHandlerImpl implements InvocationHandler {
	private ServiceImpl service;

	public ServiceInvocationHandlerImpl(Service service) {
		this.service = (ServiceImpl)service;
	}

	@Override
	public Object invoke(Object proxy, Method method, Object[] arguments) throws Throwable {
		try {
			Object result = method.invoke(service, arguments);
			if(method.getDeclaringClass() != Service.class) {
				service.getTransaction().commit();
			}
			return result;
		} catch(PersistentException e) {
			rollback(method);
			throw e;
		} catch(InvocationTargetException e) {
			rollback(method);
			throw e.getCause();
		}
	}

	private void rollback(Method method) {
		if(method.getDeclaringClass() != Service.class) {
			try {
				service.getTransaction().rollback();
			} catch(PersistentException e) {
			}
		}
	}
}
